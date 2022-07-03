#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

int indexOf(char* str, char c) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            return i;
        }
        i++;
    }
    return strlen(str);
}

char* subString(char* str, int start, int end) {
    int i = 0;
    int j = 0;
    char* newStr = (char*)malloc(sizeof(char) * (end - start + 2));
    while (i < start) {
        i++;
    }
    while (i < end) {
        newStr[j] = str[i];
        i++;
        j++;
    }
    newStr[j] = '\0';
    return newStr;
}

int strends(char* str, char* end) {
    int i = 0;
    int j = 0;
    while (str[i] != '\0') {
        if (str[i] == end[j]) {
            j++;
            if (end[j] == '\0') {
                return 1;
            }
        } else {
            j = 0;
        }
        i++;
    }
    return 0;
}

char* replaceAll(char* str, char from, char to) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == from) {
            str[i] = to;
        }
        i++;
    }
    return str;
}

#ifdef useClang
char* compiler = "clang";
#else
char* compiler = "gcc";
#endif

char* required[2048];
int requiredCount = 0;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Caesium Compiler\n");
        printf("Usage: %s <option|file> [gcc arguments]\n", argv[0]);
        printf("Options:\n");
        printf("  -h  Display this help message\n");
        printf("  -i  Output the Caesium Header Include directory\n");
        return 1;
    }
    if (strncmp(argv[1], "-", 1) == 0) {
        if (strcmp(argv[1], "-h") == 0) {
            printf("Caesium Compiler\n");
            printf("Usage: %s <option|file> [gcc arguments]\n", argv[0]);
            printf("Options:\n");
            printf("  -h  Display this help message\n");
            printf("  -i  Output the Caesium Header Include directory\n");
            return 0;
        } else if (strcmp(argv[1], "-i") == 0) {
            printf("%s/Caesium", getenv("HOME"));
            return 0;
        } else {
            printf("Caesium Compiler\n");
            printf("Usage: %s <option|file> [gcc arguments]\n", argv[0]);
            printf("Options:\n");
            printf("  -h  Display this help message\n");
            printf("  -i  Output the Caesium Header Include directory\n");
            return 1;
        }
    }

    int doCompile = strcmp(argv[2], "csg-nocomp") == 0;

    char* header_file = (char*) malloc(strlen(argv[1]) + 2);
    strcpy(header_file, argv[1]);
    strcat(header_file, ".h");

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("[CSGC] Error opening file '%s'\n", argv[1]);
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char *) malloc(size + 1);
    if (buffer == NULL)
    {
        printf("[CSGC] Error allocating memory\n");
        return 1;
    }
    fread(buffer, 1, size, file);
    fclose(file);
    buffer[size] = '\0';

    char* out_file = (char*) malloc(strlen(argv[1]) + 3);
    strcpy(out_file, argv[1]);
    strcat(out_file, ".c");

    FILE *out = fopen(out_file, "w");

    printf("[CSGC] Compiling '%s'\n", out_file);

    FILE* msg_channel = fopen("/private/var/tmp/csgc_message_channel.txt", "a");
    fprintf(msg_channel, "%s\n", out_file);
    fclose(msg_channel);

    fprintf(out, "#include <Caesium/__builtin.h>\n");

    char* token = strtok(buffer, "\n");
    int line = 1;
    while (token != NULL)
    {
        if (strncmp(token, "@", 1) == 0) {
            if (strncmp(token, "@Require", 8) == 0) {
                if (strncmp(token, "@Require \"", 10) == 0) {
                    char *require = subString(token, 10, strlen(token) - 1);
                
                    required[requiredCount] = require;
                    requiredCount++;

                    char* require_file = (char*) malloc(strlen(require) + 2);
                    strcpy(require_file, require);
                    strcat(require_file, ".c");
                    char* req_def = (char*) malloc(strlen(require_file) + 2);
                    strcat(req_def, "_");
                    strcat(req_def, require);
                    strcat(req_def, "_");
                    req_def = replaceAll(req_def, '.', '_');
                    req_def = replaceAll(req_def, '/', '_');
                    req_def = replaceAll(req_def, '\\', '_');
                    req_def = replaceAll(req_def, ':', '_');
                    req_def = replaceAll(req_def, '*', '_');
                    req_def = replaceAll(req_def, '?', '_');
                    req_def = replaceAll(req_def, '\"', '_');
                    req_def = replaceAll(req_def, '<', '_');
                    req_def = replaceAll(req_def, '>', '_');
                    req_def = replaceAll(req_def, '|', '_');
                    req_def = replaceAll(req_def, '=', '_');
                    req_def = replaceAll(req_def, ',', '_');
                    fprintf(out, "#ifndef %s\n", req_def);
                    fprintf(out, "#define %s\n", req_def);
                    
                    printf("[CSGC] Require '%s'\n", require_file);

                    msg_channel = fopen("/private/var/tmp/csgc_message_channel.txt", "a");
                    fprintf(msg_channel, "%s\n", require_file);
                    fclose(msg_channel);

                    fprintf(out, "#include \"%s\"\n", require_file);
                    fprintf(out, "#endif\n");
                    free(require_file);
                } else if (strncmp(token, "@Require <", 10) == 0) {
                    char *require = subString(token, 10, strlen(token) - 1);
                    char* require_file = (char*) malloc(strlen(require) + 2);
                    strcpy(require_file, getenv("HOME"));
                    strcat(require_file, "/Caesium/");
                    strcat(require_file, require);

                    printf("[CSGC] Import '%s'\n", require_file);
                    char* require_file_c = strdup(require_file);

                    char* req_def = (char*) malloc(strlen(require_file) + 2);
                    strcat(req_def, "_");
                    strcat(req_def, require);
                    strcat(req_def, "_");
                    req_def = replaceAll(req_def, '.', '_');
                    req_def = replaceAll(req_def, '/', '_');
                    req_def = replaceAll(req_def, '\\', '_');
                    req_def = replaceAll(req_def, ':', '_');
                    req_def = replaceAll(req_def, '*', '_');
                    req_def = replaceAll(req_def, '?', '_');
                    req_def = replaceAll(req_def, '\"', '_');
                    req_def = replaceAll(req_def, '<', '_');
                    req_def = replaceAll(req_def, '>', '_');
                    req_def = replaceAll(req_def, '|', '_');
                    req_def = replaceAll(req_def, '=', '_');
                    req_def = replaceAll(req_def, ',', '_');
                    fprintf(out, "#ifndef %s\n", req_def);
                    fprintf(out, "#define %s\n", req_def);

                    fprintf(out, "#include \"%s.c\"\n", require_file_c);
                    fprintf(out, "#endif\n");
                    required[requiredCount] = strdup(require_file_c);
                    
                    msg_channel = fopen("/private/var/tmp/csgc_message_channel.txt", "a");
                    fprintf(msg_channel, "%s.c\n", require_file_c);
                    fclose(msg_channel);

                    requiredCount++;

                    free(require_file);
                }
            } else {
                fprintf(out, "#%c%s\n", toLower(token[1]), token + 2);
            }
        } else if (strncmp(token, "fn ", 3) == 0) {
            if (strends(token, ";")) {
                char* line = (char*) malloc(strlen(token) + 1);
                strcpy(line, token);
                int ret_type_start = indexOf(line, ':');
                char* name = subString(line, 3, ret_type_start);
                char* ret_type = subString(line, ret_type_start + 1, strlen(line) - 1);
                fprintf(out, "%s %s;\n", ret_type, name);
            } else {
                char* line = (char*) malloc(strlen(token) + 1);
                strcpy(line, token);
                int ret_type_start = indexOf(line, ':');
                char* name = subString(line, 3, ret_type_start);
                char* ret_type = subString(line, ret_type_start + 1, indexOf(line, '{'));
                if (strends(line, "{")) {
                    fprintf(out, "%s %s {\n", ret_type, name);
                } else {
                    fprintf(out, "%s %s\n", ret_type, name);
                }
            }
        } else {
            fprintf(out, "%s\n", token);
        }
        token = strtok(NULL, "\n");
        line++;
    }
    free(buffer);
    fclose(out);

    for (int i = 0; i < requiredCount; i++) {
        char* require = required[i];
        char* cmd = malloc(1024);
        strcpy(cmd, "csgc ");
        strcat(cmd, require);
        strcat(cmd, " csg-nocomp");
        int reqRet = system(cmd);
        free(cmd);
        if (reqRet != 0) {
            printf("[CSGC] Error: Unable to compile '%s'\n", require);
            return 1;
        }
    }

    if (doCompile) {
        for (int i = 0; i < requiredCount; i++) {
            char* require = required[i];
            char* require_file = malloc(strlen(require) + 3);
            strcpy(require_file, require);
            strcat(require_file, ".c");
            
            msg_channel = fopen("/private/var/tmp/csgc_message_channel.txt", "a");
            fprintf(msg_channel, "%s\n", require_file);
            fclose(msg_channel);

            free(require_file);
            free(require);
        }

        return 0;
    }

    char* compilerCommand = (char*) malloc(32768);
    
    strcpy(compilerCommand, compiler);
    strcat(compilerCommand, " -I$(csgc -i)");

    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "csg-nocomp") == 0 && i == 2) {
                continue;
            }
            strcat(compilerCommand, " ");
            strcat(compilerCommand, argv[i]);
        }
    }
    
    strcat(compilerCommand, " ");
    strcat(compilerCommand, out_file);

    compilerCommand[strlen(compilerCommand)] = '\0';

    int compileResult = system(compilerCommand);

    msg_channel = fopen("/private/var/tmp/csgc_message_channel.txt", "r");
    fseek(msg_channel, 0, SEEK_END);
    long msg_channel_size = ftell(msg_channel);
    fseek(msg_channel, 0, SEEK_SET);
    char* msg_channel_buffer = malloc(msg_channel_size + 1);
    fread(msg_channel_buffer, 1, msg_channel_size, msg_channel);
    fclose(msg_channel);
    remove("/private/var/tmp/csgc_message_channel.txt");
    char* msg_channel_token = strtok(msg_channel_buffer, "\n");

    while (msg_channel_token != NULL) {
        char* require_file = malloc(strlen(msg_channel_token) + 3);
        strcpy(require_file, msg_channel_token);
        printf("[CSGC] Deleting Temp file '%s'\n", require_file);
        remove(require_file);
        free(require_file);
        msg_channel_token = strtok(NULL, "\n");
    }

    if (compileResult != 0) {
        remove(out_file);
        printf("[CSGC] Compilation failed with error code %d\n", compileResult);
        return compileResult;
    }
    printf("[CSGC] Compiled successfully!\n");
    return compileResult;
}
