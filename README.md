# -MultaUtilis
A collection of mostly self-sufficient programs each exploring an idea or feature.

* ImageSubregionAccessor
  - Structure for easy access of subimage data following the hierarchy of Mip/Texture/Face. With access using the subscript ( [ ] ) operator.
* FlipSectionData
  - Useful for instance when transforming an image; mirroring the image vertically, assuming each pixel's data is laid out contiguously going from left to right and not bottom to top. TGA and KTX file formats (which were the targets) are defined with the former.
