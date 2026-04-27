#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/matche 3.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Match3>();

    engine->Run();

    return 0;
}
