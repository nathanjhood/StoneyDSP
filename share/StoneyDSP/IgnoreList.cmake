
set(STONEYDSP_IGNORE_LIST "")
list(APPEND STONEYDSP_IGNORE_LIST

    _CPack_Packages
    CMake

    /.cache
    /.config
    /.local

    /*.zip
    /*.tar
    /*.tar.*

    /.env*
    /.git/*
    /.bak

    /.cmake
    /.dotnet
    /.github
    /.gnupg
    /.npm
    /.nvm
    /.ssh
    /.subversion
    /.vcpkg
    /.vs
    /.vscode
    /.vscode-remote-containers
    /.vscode-server
    /.w3m
    /.yarn

    /Desktop
    /Development
    /Documents
    /Downloads
    /Music
    /Pictures
    /Public
    /Templates
    /Videos

    /.bash_history
    /.bash_logout
    /.bash_profile
    /.bashrc
    /.i18n
    /.lesshst
    /.profile
    /.sudo_as_admin_successful
    /.wget-hsts
    /.yarnrc

    /doc
    /docs
    #/bin
    #/lib
    /usr

    /dist
    #/build
    #/Builds
    /install
    #/out

    /Release
    /Debug
    /MinSizeRel
    /RelWithDebInfo

    /downloads
    /packages
    /installed
    /vcpkg
    /vcpkg_installed

    /.*build.*

    /node_modules
    /package-lock.json
    /yarn.lock

    /\\\\.DS_Store
)
