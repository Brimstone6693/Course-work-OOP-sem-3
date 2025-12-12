#!/bin/bash

# Check if we're in an environment that supports GUI applications
if [ -z "$DISPLAY" ]; then
    echo "No display available. The application requires a GUI environment."
    echo "If running in a container, ensure X11 forwarding is set up or run in a GUI-enabled environment."
    exit 1
fi

echo "Starting the Software Package Database application..."
cd /workspace/database_project
./SoftwarePackageDatabase