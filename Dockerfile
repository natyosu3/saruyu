# ベースイメージ（Ubuntuの最新版）
FROM ubuntu:latest

# パッケージ情報の更新とC++開発ツールのインストール
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    vim \
    nlohmann-json3-dev \
    libpq-dev \
    && apt-get clean

# ワーキングディレクトリの設定
WORKDIR /app

# ソースコードをコンテナ内にコピー（必要なら）
# COPY . /app

# コンテナ起動時にbashを起動
CMD [ "bash" ]