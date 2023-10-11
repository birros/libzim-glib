FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        ca-certificates \
        curl \
        xz-utils \
        gcc \
        g++ \
        valac \
        meson \
        pkg-config \
        libglib2.0-dev \
        libgirepository1.0-dev \
        python3-gi \
        libxapian-dev \
        libzstd-dev \
        liblzma-dev && \
    apt-get clean && \
 	rm -rf /var/lib/apt/lists/*

# RUN curl \
#         -L https://oligarchy.co.uk/xapian/1.4.18/xapian-core-1.4.18.tar.xz \
#         -o xapian-core-1.4.18.tar.xz && \
#     tar -xvf xapian-core-1.4.18.tar.xz && \
#     cd xapian-core-1.4.18 && \
#         ./configure \
#             --prefix=/usr \
#             --disable-sse \
#             --disable-backend-chert \
#             --disable-backend-remote \
#             --disable-backend-inmemory \
#             --disable-documentation && \
#         make && \
#         make install && \
#         cd && \
#     rm -rf xapian-core*

# RUN curl \
#         -L https://github.com/facebook/zstd/releases/download/v1.4.8/zstd-1.4.8.tar.gz \
#         -o zstd-1.4.8.tar.gz && \
#     tar -xvf zstd-1.4.8.tar.gz && \
#     cd zstd-1.4.8/build/meson && \
#         meson setup \
#             --prefix=/usr \
#             --libdir=lib \
#             -Dbin_programs=false \
#             -Dbin_contrib=false \
#             build && \
#         ninja -C build && \
#         ninja -C build install && \
#         cd && \
#     rm -rf zstd*

RUN curl \
        -L https://github.com/openzim/libzim/archive/6.2.2.tar.gz \
        -o libzim-6.2.2.tar.gz && \
    tar -xvf libzim-6.2.2.tar.gz && \
    cd libzim-6.2.2 && \
        meson setup \
            --prefix=/usr \
            --libdir=lib \
            --wrap-mode=nodownload \
            build && \
        ninja -C build && \
        ninja -C build install && \
        cd && \
    rm -rf libzim*
