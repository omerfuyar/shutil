#define SHUC_NO_RUN_LOG
#define SHU_IMPLEMENTATION
#include "../../shu/shu.h"
#include "../../shuild/shuild.h"

#ifdef _WIN32
#define LINUX_SUFFIX ""
#else
#define LINUX_SUFFIX ".ignore"
#endif

void ShuildExample(const char *name)
{
    char buffer[64] = {0};

    snprintf(buffer, sizeof(buffer), "%s%s", name, LINUX_SUFFIX);
    SHU_ModuleBegin(buffer, NULL);

    snprintf(buffer, sizeof(buffer), "%s.c", name);
    SHU_ModuleAddSourceFile(buffer);

    SHU_ModuleCompile(NULL, SHUModuleType_Executable);
}

int main(int argc, char **argv)
{
    SHU_CompilerTryConfigure("gcc");
    SHU_UtilAutomate(argc, argv);

    SHU_CompilerAddFlags(SHUM_FLAGS_OPTIMIZATION_HIGH);
    SHU_CompilerAddFlags("-Wno-unused-function -Wno-format-truncation");

    ShuildExample("SHUArray");

    return 0;
}