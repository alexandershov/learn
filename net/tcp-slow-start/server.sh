set -euf -o pipefail

if [ "${#}" -ne 1 ];
then
    echo "usage: listen.sh PORT"
    exit 1
fi

port="${1}"
yes data | nc -l "${port}"
