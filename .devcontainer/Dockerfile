FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12

RUN apt-get update && \
    export DEBIAN_FRONTEND=noninteractive && \
    apt-get -y install --no-install-recommends \
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
        liblzma-dev \
        libicu-dev \
        libvala-0.56-dev \
        libjsonrpc-glib-1.0-dev \
        libgee-0.8-dev && \
    apt-get clean && \
 	rm -rf /var/lib/apt/lists/*

RUN curl \
        -L https://github.com/uncrustify/uncrustify/archive/refs/tags/uncrustify-0.77.1.tar.gz \
        -o uncrustify-0.77.1.tar.gz && \
    tar -xvf uncrustify-0.77.1.tar.gz --exclude="tests" && \
    cd uncrustify-uncrustify-0.77.1 && \
        mkdir build && \
        cd build && \
            cmake \
                -DCMAKE_BUILD_TYPE=Release \
                -DBUILD_TESTING=false \
                -DCMAKE_INSTALL_PREFIX=/usr \
                -DCMAKE_INSTALL_LIBDIR=lib \
                .. && \
            make && \
            make install && \
            cd && \
    rm -rf uncrustify*

RUN curl \
        -L https://github.com/vala-lang/vala-language-server/releases/download/0.48.7/vala-language-server-0.48.7.tar.xz \
        -o vala-language-server-0.48.7.tar.xz && \
    tar -xvf vala-language-server-0.48.7.tar.xz && \
    cd vala-language-server-0.48.7 && \
        meson setup \
            --prefix=/usr \
            --libdir=lib \
            build && \
        meson compile -C build && \
        meson install -C build && \
        cd && \
    rm -rf vala-language-server*

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
        -L https://github.com/openzim/libzim/archive/7.2.2.tar.gz \
        -o libzim-7.2.2.tar.gz && \
    tar -xvf libzim-7.2.2.tar.gz && \
    cd libzim-7.2.2 && \
        meson setup \
            --prefix=/usr \
            --libdir=lib \
            --wrap-mode=nodownload \
            build && \
        ninja -C build && \
        ninja -C build install && \
        cd && \
    rm -rf libzim*
