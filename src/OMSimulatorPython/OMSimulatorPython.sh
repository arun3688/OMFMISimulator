#!/bin/sh
# get the script location and retrive the absolute path
SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
# set the python path and Library path
export PYTHONPATH=$SCRIPTPATH/../lib:$PYTHONPATH 
export LD_LIBRARY_PATH=$SCRIPTPATH/../lib:$LD_LIBRARY_PATH
python $@
