# !/bin/bash
# cli - args . bash

source CombineFiles.sh temp.txt $1 $2
wc temp.txt
rm temp.txt
