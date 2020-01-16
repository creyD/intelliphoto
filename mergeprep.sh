# Run CPP Check
echo "Running CPPCheck..."
cppcheck --enable=all --output-file=cppcheck_errors.txt src/
cppcheck --check-config --output-file=cppcheck_config.txt src/
echo "CPPCheck finished"
# Uncrustify Files
echo "Running Uncrustify..."
find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -c conf/uncrustify.cfg --no-backup {} +
echo "Uncrustify finished."
# Adding changes to git
echo "Committing Changes to Git..."
git add '*'
git commit -m "Automated Merge Preparation"
echo "Committed."
echo "Finished."
