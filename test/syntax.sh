THIS_DIR="$(cd "$(dirname ${BASH_SOURCE[0]})";pwd -P)"
HPP_DIR=$THIS_DIR/../include/cppcompat
uname -a |grep -q Darwin && {
  CFLAGS=--sysroot=$(xcrun --show-sdk-path --sdk macosx)
}
for std in 11 14 1z; do
  echo "checking std c++$std"
  for hpp in $HPP_DIR/*.hpp; do
    echo "$hpp"
    ${CXX:=clang++} $CFLAGS -std=c++$std -fsyntax-only $hpp $@
  done
done