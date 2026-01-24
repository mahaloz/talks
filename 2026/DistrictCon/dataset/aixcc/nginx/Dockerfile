FROM gcr.io/oss-fuzz-base/base-clang@sha256:2310a8bff38b21009e537a56825d3206cfaac18ba4ccdd23539f5e136ce83148

# global environment variables
ENV LC_ALL C.UTF-8
ENV LANG C.UTF-8
ENV TZ America/New_York
ENV USER root

# get common ubuntu packages that all containers must have, and
# setup gosu binary to modify user permissions in the container
RUN set -eux; \
    DEBIAN_FRONTEND=noninteractive apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        gettext-base \
        gosu \
        sudo \
        && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/* && \
    # verify that the binary works
    gosu nobody true

# nginx deps
RUN DEBIAN_FRONTEND=noninteractive apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
    build-essential \
    pkg-config \
    gcc \
    git \
    libelf-dev \
    make  \
    perl-base \
    rsync \
    libpcre3-dev \
    zlib1g-dev \
    libz-dev \
    libgd3 \
    libgd-dev \
    libgd-perl \
    libssl-dev \
    && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/* && \
    echo "yes" | cpan install GD


    
RUN cp /usr/local/lib/clang/18/lib/x86_64-unknown-linux-gnu/libclang_rt.fuzzer.a /usr/lib/libFuzzingEngine.a && \
    cp /usr/local/lib/clang/18/lib/x86_64-unknown-linux-gnu/libclang_rt.asan.a /usr/lib/libasan.a

# $BINS = directory to store build and run scripts
# $SRC  = directory to store source code
# $OUT  = directory to store build artifacts (harnesses, test binaries)
# $WORK = directory to store intermediate files
ENV BINS=/usr/local/sbin/container_scripts
ENV SRC=/src
ENV OUT=/out
ENV WORK=/work
ENV LIB_FUZZING_ENGINE="/usr/lib/libFuzzingEngine.a"

# Create needed directories
RUN mkdir -p $OUT $WORK $SRC $BINS && chmod -R 0755 $OUT $WORK $SRC $BINS && \
    mkdir -p $OUT/html && \
    mkdir -p $OUT/logs