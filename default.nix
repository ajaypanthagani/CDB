{ pkgs ? import <nixpkgs> {} }:

let
  myTarball = builtins.fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/e08a8231e2c827f586e64727c1063c5e61dbc00d.tar.gz";
  };

  altPkgs = import myTarball {};
  myCMake = altPkgs.cmake;
in

pkgs.stdenv.mkDerivation {
  name = "cdb";
  src = ./.;

  buildInputs = [
    pkgs.openssl
    pkgs.boost
    pkgs.abseil-cpp
    pkgs.protobuf3_21
    pkgs.grpc
  ];

  nativeBuildInputs = [
    myCMake
    pkgs.pkg-config
  ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DBUILD_SHARED_LIBS=ON"
    "-DCMAKE_CXX_FLAGS=-fPIC"
  ];

  # installPhase = ''
  #   mkdir -p $out/include
  #   mv src/proto/*.pb.cc $out/include
  #   mv src/proto/*.pb.h $out/include
  #   mkdir -p $out/bin
  #   cp cdb $out/bin/
  # '';
  installPhase = ''
    mkdir -p $src/build
    mv ./* $src/build
  '';
}
