#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <dir> <string>"
    exit 1
fi

FILE_PATH="$1"
WRITE_STR="$2"

# Create the parent directory if it doesn't exist
mkdir -p "$(dirname "$FILE_PATH")"

# Create the file if it doesn't exist, then write to it
echo "$WRITE_STR" > "$FILE_PATH"

