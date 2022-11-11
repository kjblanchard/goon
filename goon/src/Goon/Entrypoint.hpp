#ifdef GN_PLATFORM_MACOS
extern Goon::Application *Goon::CreateApplication();

int main(int argc, char** argv)
{
    Goon::Log::Init();
    int a = 5;
    GN_CORE_WARN("NO U R ERROR");
    GN_TRACE("Variable is {0}", a);
    auto app = Goon::CreateApplication();
    app->Run();
    delete app;
}
#endif

