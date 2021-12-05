#!/bin/bash

bold=$(tput bold)
normal=$(tput sgr0)
i_path="/opt/ctemplate/"

# Usage info
show_help() {
	echo -e "CTemplate - Create new C templates for your projects!"
	echo -e "Usage: ${0##*/} [-s] [-p PATH]\n"
	echo -e "\t-h\tshow brief help"
	echo -e "\t-s\tcreate a new client-server template (${bold}OPTIONAL${normal})"
	echo -e "\t-p\tspecify the directory to store the new template (${bold}OPTIONAL${normal})"
	echo -e "\n${bold}NOTE:${normal} If -p is not used, the template it will be stored in the current directory."
}

exit_abnormal() {
	echo -e "Usage: ${0##*/} [-s] [-p PATH]"
}

s_flag=''
p_flag=''
path=''

OPTIND=1

while getopts 'hsp:path' opt; do
	case $opt in
		h)
			show_help
        	exit 0
			;;
		s)
			s_flag='true'
			;;
		p)
			p_flag='true'
			path="${OPTARG}"
			;;
		*)
			exit_abnormal >&2
			exit 1
			;;
	esac
done

if [ ! -z "$s_flag" ]; then
	if [ ! -z "$p_flag" ]; then
		cp --preserve $i_path/template_s/* $path
	fi
	cp --preserve $i_path/template_s/* $PWD
else
	if [ ! -z "$p_flag" ]; then
		cp --preserve $i_path/template/* $path
	fi
	cp --preserve $i_path/template/* $PWD
fi

shift "$((OPTIND-1))"

echo -e "Copying the necessary files..."
echo -e "[SUCCESS] Template successfully imported!"

#End of script
