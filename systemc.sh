#!/bin/sh

export SYSTEMC_HOME=/home/aleksa/systemC/systemc-2.3/
export LD_LIBRARY_PATH="$SYSTEMC_HOME/lib-linux64"
CPP="$@"
SIM="sim"

echo "g++ -I. -I$SYSTEMC_HOME/include -L. -L$LD_LIBRARY_PATH -o "$SIM" "$CPP" -lsystemc -lm"

g++ -I. -I$SYSTEMC_HOME/include -L. -L"$LD_LIBRARY_PATH" -o "$SIM" "$CPP" -lsystemc -lm

./$SIM
