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
