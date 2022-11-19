#ifdef GN_PLATFORM_MACOS

extern Goon::Application *Goon::CreateApplication();

int main(int argc, char** argv)
{
    Goon::Log::Init();
    auto app = Goon::CreateApplication();
    app->Run();
    delete app;
}
#endif

