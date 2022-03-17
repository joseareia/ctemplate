#!/bin/bash

if [ ! -d "/opt" ]; then
    sudo mkdir /opt
fi

if [ -d "/opt/ctemplate" ]; then
    sudo rm -r /opt/ctemplate
    sudo rm -r /usr/local/bin/ctemplate
fi

sudo mkdir /opt/ctemplate

echo -e "Copying the files to /opt/ctemplate..."
sudo cp --preserve -r template_s /opt/ctemplate
sudo cp --preserve -r template /opt/ctemplate
sudo cp --preserve ctemplate.sh /opt/ctemplate

echo -e "Creating a symlink of 'ctemplate.sh' to /usr/local/bin/ctemplate..."
sudo ln -s /opt/ctemplate/ctemplate.sh /usr/local/bin/ctemplate

echo -e "[SUCCESS] Installation complete!"
