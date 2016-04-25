# protolite

##### *Fast and Simple Object Serialization to Protocol Buffers*

[![Build Status](https://travis-ci.org/jeroenooms/protolite.svg?branch=master)](https://travis-ci.org/jeroenooms/protolite)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/jeroenooms/protolite?branch=master&svg=true)](https://ci.appveyor.com/project/jeroenooms/protolite)
[![Coverage Status](https://codecov.io/github/jeroenooms/protolite/coverage.svg?branch=master)](https://codecov.io/github/jeroenooms/protolite?branch=master)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/protolite)](https://cran.r-project.org/package=protolite)
[![CRAN RStudio mirror downloads](http://cranlogs.r-pkg.org/badges/protolite)](https://cran.r-project.org/package=protolite)
[![Github Stars](https://img.shields.io/github/stars/jeroenooms/protolite.svg?style=social&label=Github)](https://github.com/jeroenooms/protolite)

> An optimized, permissively licensed C++ implementation for serializing
  R objects to protocol-buffers. This package is complementary to the much larger
  'RProtoBuf' package which provides a full featured toolkit for working with
  protocol-buffers in R.
  
## See Also

This small package contains an optimized C++ implementation for serializing R objects to the [`rexp.proto`](https://github.com/jeroenooms/protolite/blob/master/src/rexp.proto) schema. Exactly the same `serialize_pb` functionality can also be found in the much larger RProtoBuf package, though the version in `protolite` is significantly faster.

For an easy and fast solution to serialize R data to a generic proto schema, the `protolite` package might suffice. To take advantage of the full power of prototol buffers you need the `RProtoBuf` package, which provides a complete toolkit for working with protocol-buffers in R. With `RProtoBuf` you can create new protocol buffers of a schema, read in .proto files, manipulate fields with type checking that they match the schema, and generate or parse .prototext ascii format protocol buffers. Also have a look at our paper [*RProtoBuf: Efficient Cross-Language Data Serialization in R*](http://arxiv.org/abs/1401.7372).

## Hello World

```r
# Serialize and unserialize an object
library(protolite)
buf <- serialize_pb(iris)
out <- unserialize_pb(buf)
stopifnot(identical(iris, out))

# Fully compatible with RProtoBuf
buf <- RProtoBuf::serialize_pb(iris, NULL)
out <- protolite::unserialize_pb(buf)
stopifnot(identical(iris, out))

# Other way around
buf <- protolite::serialize_pb(mtcars, NULL)
out <- RProtoBuf::unserialize_pb(buf)
stopifnot(identical(mtcars, out))

```

## Installation

Binary packages for __OS-X__ or __Windows__ can be installed directly from CRAN:

```r
install.packages("protolite")
```

Installation from source on Linux or OSX requires Google's [Protocol Buffers](https://developers.google.com/protocol-buffers/) library. On __Debian or Ubuntu__ install [libprotobuf-dev](https://packages.debian.org/testing/libprotobuf-dev) and [protobuf-compiler](https://packages.debian.org/testing/protobuf-compiler):

```
sudo apt-get install -y libprotobuf-dev protobuf-compiler
```

On __Fedora__ we need [protobuf-devel](https://apps.fedoraproject.org/packages/protobuf-devel):

```
sudo yum install protobuf-devel
````

On __CentOS / RHEL__ we install [protobuf-devel](https://apps.fedoraproject.org/packages/protobuf-devel) via EPEL:

```
sudo yum install epel-release
sudo yum install protobuf-devel
```

On __OS-X__ use [protobuf](https://github.com/Homebrew/homebrew-core/blob/master/Formula/protobuf.rb) from Homebrew:

```
brew install protobuf
```
