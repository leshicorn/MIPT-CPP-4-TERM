#!/usr/bin/env bash

CONTEST_NUMBER=$1
START=$2
END=$3

# if $4 is not specified
MAKE_TEMPLATE_FILENAME="templates/default_make.template"
TEMPLATE_FILENAME="templates/default.template"
if [ -z "$4" ]
then
    echo "No argument supplied"
    echo "Using default template"
else
    TEMPLATE_FILENAME="templates/$4.template"
fi

mkdir "contest$CONTEST_NUMBER"
echo "Created folder contest$CONTEST_NUMBER"
for ((i=START; i < END; i++)) do
    REL_FILE_PATH="contest$CONTEST_NUMBER/task$i.cpp"
    touch $REL_FILE_PATH
    echo "Created file $REL_FILE_PATH"

    # if file is not empty
    if [ -s $REL_FILE_PATH ]
    then
        echo "File $REL_FILE_PATH is not empty"
    else
        cat $TEMPLATE_FILENAME > $REL_FILE_PATH
        echo "Filled file $REL_FILE_PATH with $TEMPLATE_FILENAME"
    fi
done


#create Makefile in the directory if it doesn't exist
REL_MAKEFILE_PATH="contest$CONTEST_NUMBER/Makefile"
if [ -s $REL_MAKEFILE_PATH ]
then
    echo "File $REL_MAKEFILE_PATH is not empty"
else
    cat $MAKE_TEMPLATE_FILENAME > $REL_MAKEFILE_PATH
    echo "Filled file $REL_MAKEFILE_PATH with $MAKE_TEMPLATE_FILENAME"
fi

echo "Done!"