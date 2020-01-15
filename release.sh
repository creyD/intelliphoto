# Discarding local changes
git reset --hard
# Run CPP Check
echo "Running CPPCheck..."
cppcheck --enable=all --output-file=cppcheck_errors.txt src/
echo "CPPCheck finished"
# Uncrustify Files
echo "Running Uncrustify..."
find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -c conf/uncrustify.cfg --no-backup {}
echo "Uncrustify finished."
# Run Unit Tests
echo "Running unit tests..."

echo "Finished unit testing."
# Remove Overhead Folders/ Files
echo "Cleaning directory..."
rm -r src/build-*
rm -r build-*/
rm -r Examples/
rm src/IntelliPhoto.pro.user
echo "Directory cleaned."
# Run Doxygen
echo "Running Doxygen..."
doxygen conf/intelliphoto_dox
echo "Doxygen finished."
# Building
qmake src/IntelliPhoto.pro -spec macx-clang CONFIG+=debug CONFIG+=x86_64 CONFIG+=qml_debug && make qmake_all
make -j4 build-IntelliPhoto-Desktop_Qt_5_14_0_clang_64bit-Debug
make clean -j4 build-IntelliPhoto-Desktop_Qt_5_14_0_clang_64bit-Debug
