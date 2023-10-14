VERSION=0.4
URL=https://github.com/openzim/zim-testing-suite/releases/download/v${VERSION}/zim-testing-suite-${VERSION}.tar.gz
SHA256=c4c8f0c157b21b8e0c81ce016d2a92b528b2972acb76d5a5d9e04d934fa2e742
DEST_FILENAME=zim-testing-suite-${VERSION}.tar.gz

all: download

.PHONY: download
download: zim-testing-suite-${VERSION}

zim-testing-suite-${VERSION}: ${DEST_FILENAME}
	rm -rf zim-testing-suite-${VERSION}
	tar -xvf ${DEST_FILENAME}
	touch zim-testing-suite-${VERSION}

${DEST_FILENAME}:
	rm -f *.tmp
	curl -L ${URL} --output ${DEST_FILENAME}.tmp
	echo '${SHA256}  ${DEST_FILENAME}.tmp' | sha256sum -c
	mv ${DEST_FILENAME}.tmp ${DEST_FILENAME}
