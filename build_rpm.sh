#!/bin/bash
set -x
rpm_build_dir="$HOME/rpmbuild"

if [[ -z ${RTPENGINE_VER} ]]; then
    if [[ ! -z $1 ]]; then
        RTPENGINE_VER=$1
    else
        echo "version is empty"
        exit 1
    fi
fi
mcn_branch="${RTPENGINE_VER}-mcn"
echo "version: ${RTPENGINE_VER}"

if [[ -z $(git branch --list ${mcn_branch}) ]]; then
    echo "Branch $mcn_branch doesn't exist."
    exit 1
fi

src_dir="${rpm_build_dir}/SOURCES"
mkdir -p "$src_dir"

git archive --output "${src_dir}/ngcp-rtpengine-${RTPENGINE_VER}+0~mr${RTPENGINE_VER}.tar.gz" --prefix="ngcp-rtpengine-${RTPENGINE_VER}+0~mr${RTPENGINE_VER}/" "${mcn_branch}"
rpmbuild -ta "${src_dir}/ngcp-rtpengine-${RTPENGINE_VER}+0~mr${RTPENGINE_VER}.tar.gz"
