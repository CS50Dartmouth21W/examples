#!/bin/bash
# 
# comics: build the index page for the CS50 Comics.
# Creates index.md to refer to *.{jpg,jpeg,png,gif,tif,tiff,pdf}
#
# David Kotz, March 2019

cat > index.md <<EOF
# Comics

A few fun comics related to this course.

EOF

# see https://www.gnu.org/software/bash/manual/html_node/The-Shopt-Builtin.html
shopt -s nullglob

for img in *.{jpg,jpeg,png,gif,tif,tiff,pdf}
do
    echo "![]($img)" >> index.md
    echo >> index.md
done

exit 0
