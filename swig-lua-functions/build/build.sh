#!/bin/bash

swig -c++ -lua -o vec_wrap.cxx -outdir temp ../src/vec.i
