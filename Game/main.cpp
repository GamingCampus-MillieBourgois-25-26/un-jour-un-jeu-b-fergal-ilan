#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/Fbuller_hell.h"
#include "Scenes/FTowerdef.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<FTowerDef>(); ///FTowerDef ,  FBHene

    engine->Run();

    return 0;
}
