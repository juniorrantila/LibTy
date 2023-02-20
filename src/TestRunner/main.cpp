#include <Unit/RunAllTests.h>
#include <Unit/TestCase.h>
#include <Unit/TestContext.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace {

using u32 = unsigned int;
using c_string = char const*;

struct UserContext {
    Unit::TestContext test_context();
    void set_suite_name_from_path(c_string path);

private:
    void init(u32 size);
    void deinit() const;
    void test_started(u32 id, c_string name);
    void test_finished(u32 id, c_string message);

    void rewind() const;
    void show_stats() const;
    void update(u32 id) const;
    void last_update() const;
    void log_failed_tests() const;

    bool did_fail() const { return m_failure_size != 0; }

    c_string m_suite_name { 0 };
    c_string* m_results { 0 };
    c_string* m_names { 0 };
    u32* m_failure_ids { 0 };

    u32 m_failure_size { 0 };
    u32 m_success_size { 0 };
    u32 m_total_tests { 0 };
};

template <typename T>
T* alloc_array(u32 size)
{
    return (T*)calloc(size, sizeof(T));
}

}

int main(int argc, c_string* argv)
{
    u32 test_suites_size = argc - 1;
    c_string* test_suite_paths = &argv[1];

    printf("\033[34mSuites\033[0m:\n");
    for (u32 i = 0; i < test_suites_size; i++)
        printf("  %s\n", test_suite_paths[i]);

    auto* user_contexts
        = alloc_array<UserContext>(test_suites_size);
    using RunSuite = decltype(unit_run_all_tests)*;
    auto* run_suites = alloc_array<RunSuite>(test_suites_size);
    auto* test_suites = alloc_array<void*>(test_suites_size);

    for (u32 i = 0; i < test_suites_size; i++) {
        user_contexts[i].set_suite_name_from_path(
            test_suite_paths[i]);
        test_suites[i] = dlopen(test_suite_paths[i], RTLD_LAZY);
        if (!test_suites[i]) {
            printf("Could not open %s: %s\n", test_suite_paths[i],
                dlerror());
            return 1;
        }
        run_suites[i] = (RunSuite)dlsym(test_suites[i],
            UNIT_TEST_RUNNER_NAME);
        c_string error = dlerror();
        if (error) {
            printf("\033[31mError\033[0m: %s\n", error);
            return 1;
        }
    }

    for (u32 i = 0; i < test_suites_size; i++) {
        run_suites[i](user_contexts[i].test_context());
    }
}

namespace {

void UserContext::set_suite_name_from_path(c_string path)
{
    auto size = strlen(path);
    u32 last_slash = 0;
    for (u32 i = size; --i != 0;) {
        if (path[i] == '/') {
            last_slash = i;
            break;
        }
    }
    m_suite_name = &path[last_slash + 1];
}

void UserContext::init(u32 size)
{
    m_total_tests = size;
    m_results = (c_string*)malloc(sizeof(c_string) * size);
    m_names = (c_string*)malloc(sizeof(c_string) * size);
    m_failure_ids = (u32*)malloc(sizeof(u32) * size);
}

void UserContext::last_update() const
{
    rewind();
    show_stats();
    if (did_fail()) {
        printf("\033[31mfailure\033[0m\n");
    } else {
        printf("\033[32msuccess\033[0m\n");
    }
    log_failed_tests();
}

void UserContext::deinit() const
{
    last_update();
    free(m_failure_ids);
    free(m_names);
    free(m_results);
}

void UserContext::test_started(u32 id, char const* name)
{
    m_names[id] = name;
    update(id);
}

void UserContext::test_finished(u32 id, char const* message)
{
    m_results[id] = message;
    if (!message) {
        m_success_size++;
    } else {
        m_failure_ids[m_failure_size++] = id;
    }
    update(id);
}

void UserContext::rewind() const { printf("\r\033[2K"); }

void UserContext::show_stats() const
{
    printf("\033[31m%d\033[0m/\033[32m%d\033[0m/%d: %16s: ",
        m_failure_size, m_success_size, m_total_tests,
        m_suite_name);
    (void)fflush(stdout);
}

void UserContext::update(u32 id) const
{
    rewind();
    show_stats();
    printf("%s", m_names[id]);
    (void)fflush(stdout);
}

void UserContext::log_failed_tests() const
{
    if (m_failure_size == 0)
        return;
    printf("Failed tests:\n");
    for (u32 index = 0; index < m_failure_size; index++) {
        auto id = m_failure_ids[index];
        printf("  %s: %s\n", m_names[id], m_results[id]);
    }
}

Unit::TestContext UserContext::test_context()
{
    return Unit::TestContext {
        .user_context = this,

        .on_init =
            [](void* context, auto number_of_tests) {
                auto& self = *(UserContext*)context;
                self.init(number_of_tests);
            },

        .on_deinit =
            [](void* context) {
                auto& self = *(UserContext*)context;
                self.deinit();
            },

        .on_test_started =
            [](void* context, auto id, auto name) {
                auto& self = *(UserContext*)context;
                self.test_started(id, name);
            },

        .on_test_finished =
            [](void* context, auto id, auto message) {
                auto& self = *(UserContext*)context;
                self.test_finished(id, message);
            },
    };
}

}
