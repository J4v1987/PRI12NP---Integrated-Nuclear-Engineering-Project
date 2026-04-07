#!/bin/bash

# Ensure we are in the git root even if called from a subfolder
# The double quotes handle spaces in your "M1S2 projects" path
cd "$(git rev-parse --show-toplevel)" || exit

# The directory you want to target
TARGET_DIR="TP GEANT4/B2a/B2a-2"

echo "Generating raw GitHub links for: $TARGET_DIR"
echo "------------------------------------------------"

# Generate the links
git ls-files --full-name "$TARGET_DIR" | while read -r file; do
    # URL encode the filename for browser compatibility
    encoded_file=$(python3 -c "import urllib.parse, sys; print(urllib.parse.quote(sys.argv[1]))" "$file")
    echo "https://raw.githubusercontent.com/J4v1987/PRI12NP---Integrated-Nuclear-Engineering-Project/main/$encoded_file"
done
