{
  description = "dev-env for 42 projects";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    bash-5-1-p16 = {
      url = "github:nixos/nixpkgs?rev=79b3d4bcae8c7007c9fd51c279a8a67acfa73a2a";
    };
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
  };

  outputs = {
    self,
    nixpkgs,
    bash-5-1-p16,
    flake-utils
  }: flake-utils.lib.eachDefaultSystem
    (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        stdenv = pkgs.stdenvAdapters.useMoldLinker pkgs.clang17Stdenv;
      in
      {
        devShell = (pkgs.mkShell.override { inherit stdenv; }) {
          buildInputs = with pkgs; [
            readline
          ];
          nativeBuildInputs = with pkgs; [
            flex
            bison
            bash-5-1-p16.legacyPackages.${system}.bash

            cloc

            valgrind
            gdb
          ];
        };
      }
    );
}
# vim: ts=2 sw=2 et

