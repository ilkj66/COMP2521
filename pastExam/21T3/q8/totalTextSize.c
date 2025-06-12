
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fs.h"
int _sumText(File file) {
    if (file == NULL) return 0;

    if (file->type == TEXT_FILE) {
        return file->text ? strlen(file->text) : 0;
    }

    // DIRECTORY 类型
    int total = 0;
    FileList curr = file->files;
    while (curr != NULL) {
        total += _sumText(curr->file);
        curr = curr->next;
    }
    return total;
}

int totalTextSize(Fs fs) {
    if (fs == NULL || fs->root == NULL) return 0;
    return _sumText(fs->root);
}
