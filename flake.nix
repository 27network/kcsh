{
  description = "dev-env for kcsh";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    matching42pkgs.url = "github:nixos/nixpkgs?rev=79b3d4bcae8c7007c9fd51c279a8a67acfa73a2a";
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
  };

  outputs = {
    self,
    nixpkgs,
    matching42pkgs,
    flake-utils
  }: flake-utils.lib.eachDefaultSystem
    (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        pkgs42 = matching42pkgs.legacyPackages.${system};
        stdenv = pkgs.stdenvAdapters.useMoldLinker pkgs.llvmPackages_18.stdenv;
      in
      {
        devShell = (pkgs.mkShell.override { inherit stdenv; }) {
          buildInputs = with pkgs; [
            pkgs42.readline
          ];
          nativeBuildInputs = with pkgs42; [
            readline
            bash
          ] ++ (with pkgs; [
            aflplusplus
            cloc
            valgrind
            gdb
          ]);
        };
      }
    );
}
# vim: ts=2 sw=2 et

