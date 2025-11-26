/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
/*
 * Copyright 2023 Saso Kiselkov. All rights reserved.
 */

#![allow(clippy::uninlined_format_args)]

use build_target::{target_os, Os};

#[allow(dead_code)]
fn add_test_config() {
    let os = target_os().unwrap();
    let (plat_short, plat_long) = match os {
        Os::Windows => ("win64", "win-64"),
        Os::Linux => ("lin64", "linux-64"),
        Os::MacOs => ("mac64", "mac-64"),
        _ => unreachable!(),
    };
    let root_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();
    println!("cargo:rustc-link-search=native={root_dir}/../qmake/{plat_short}");
    println!("cargo:rustc-link-lib=static=acfutils");

    println!(
        "cargo:rustc-link-search=native={}/../curl/libcurl-{}/lib",
        root_dir, plat_long,
    );
    println!("cargo:rustc-link-lib=static=curl");

    println!(
        "cargo:rustc-link-search=native={}/../ssl/openssl-{}/lib",
        root_dir, plat_long,
    );
    println!("cargo:rustc-link-lib=static=crypto");
    println!("cargo:rustc-link-lib=static=ssl");

    println!(
        "cargo:rustc-link-search=native={}/../zlib/zlib-{}/lib",
        root_dir, plat_long,
    );
    println!("cargo:rustc-link-lib=static=z");

    if os == Os::Windows {
        println!("cargo:rustc-link-lib=advapi32");
        println!("cargo:rustc-link-lib=crypt32");
        println!("cargo:rustc-link-lib=bcrypt");
        println!("cargo:rustc-link-lib=psapi");
    }
}

fn main() {
    add_test_config();
}
