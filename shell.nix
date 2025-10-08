{
  pkgs ? import <nixpkgs> { },
}:
pkgs.callPackage (
  {
    mkShell,
    rustc,
    rustPlatform,
    rustfmt,
    clippy,
    rust-analyzer,
  }:
  mkShell {
    nativeBuildInputs = with pkgs; [
      git

      # Java
      jdk

      # Rust
      rustc
      cargo
      rustfmt
      clippy
      rust-analyzer
    ];

    RUST_SRC_PATH = "${rustPlatform.rustLibSrc}";
  }
) { }
