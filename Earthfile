VERSION 0.7

deps:
    FROM debian:12

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
            libicu-dev && \
        apt-get clean && \
        rm -rf /var/lib/apt/lists/*

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

tests:
    FROM +deps
    COPY . .
    RUN meson setup -Dtests=true build
    RUN meson compile -C build
    RUN meson test -C build
