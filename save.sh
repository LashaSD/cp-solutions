#!/usr/bin/bash

set -e

if [ $# -ne 1 ]; then
    echo "Usage: $0 <site-round-problem>"
    exit 1
fi

IFS='-' read -r site round problem <<< "$1"

if [ ! -f solve.cpp ]; then
    echo "Error: solve.cpp not found!"
    exit 1
fi

if [ ! -f solve-template.cpp ]; then
    echo "Error: solve-template.cpp not found!"
    exit 1
fi

dest_dir="$site/$round"
dest_file="$dest_dir/${problem}.cpp"

if [ -f "$dest_file" ]; then
    echo "Conflict: File '$dest_file' already exists. Aborting."
    exit 1
fi

mkdir -p "$dest_dir"

mv solve.cpp "$dest_file"
cp "$dest_file" solve.cpp.bk
cp solve-template.cpp solve.cpp

echo "Moved solve.cpp to $dest_file"
echo "Backed up as solve.cpp.bk"
echo "Replaced solve.cpp with solve-template.cpp"
