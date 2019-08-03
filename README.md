# -MultaUtilis
A collection of mostly self-sufficient programs each exploring an idea or feature.

* ImageSubregionAccessor
  - Structure for easy access of an element in a linearly arranged array. Where the array is following a hierarchy of Level/Element/Face, where each region takes up one element. E.g. level0 element0 face0 face1 element1 face0 face1.
   
    *Now redesigned for better performance.*
   
* FlipSectionData
  - Useful for instance when transforming an image; mirroring the image vertically, assuming each pixel's data is laid out contiguously going from left to right and not bottom to top. TGA and KTX file formats (which were the targets) are defined with the former.
