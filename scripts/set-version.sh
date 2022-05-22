#!/bin/sh

set -eu

usage() {
    echo "Syntax: ./scripts/set-version.sh 1.0.0"
    exit 1
}

# Check if the version argument was passed.
if [ "$#" -ne 1 ]; then
    usage
fi

# Replace the version.
sed -i "s/mailbridge VERSION \".*\"/mailbridge VERSION \"$1\"/" CMakeLists.txt