#!/bin/bash
svn st $1 | egrep '^[A|M]' | cut -d' ' -f8- > svn-changelist

