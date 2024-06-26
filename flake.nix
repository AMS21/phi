{
  description = "Phi";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
        };
        llvm = pkgs.llvmPackages_18;
      in {
        devShell = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } rec {
          packages = with pkgs; [
            clang-tools_18
            clang_18
            cmake
            cmake-format
            cppcheck
            gdb
            include-what-you-use
            llvm.libcxx
            llvm.lldb
            ninja
            valgrind
          ];
        };
      }
    );
}
