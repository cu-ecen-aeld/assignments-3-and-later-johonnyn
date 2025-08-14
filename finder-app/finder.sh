#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <dir> <string>"
    exit 1
fi

FILES_DIR="$1"
SEARCH_STR="$2"

if [ ! -d "$FILES_DIR" ]; then
    echo "Directory does not exist"
    exit 1
fi

FILE_COUNT=$(find "$FILES_DIR" -type f | wc -l)
MATCH_COUNT=$(grep -r -F --include="*" "$SEARCH_STR" "$FILES_DIR" 2>/dev/null | wc -l)

echo "The number of files are $FILE_COUNT and the number of matching lines are $MATCH_COUNT"
    


