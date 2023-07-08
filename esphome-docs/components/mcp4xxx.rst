MCP4xxx Component
=================

.. seo::
    :description: Instructions for setting up MCP42xx component on the ESP.

The MCP4xxx component (`datasheet<https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/22060b.pdf>`,
`Digi-Key<https://www.digikey.de/en/products/detail/microchip-technology/mcp4252-503e-p/1635667>`) provides an interface
to the `7/8-Bit Single/Dual SPI Digital POT with Volatile Memory`.

.. code-block:: yaml

    # Example configuration entry

    # Setup a mcp4xxx device using the SPI bus
    mcp4xxx:
        id: mcp4xxx_chip
        # optional
        # cs_pin: SS
        # This value is intended for calculations to be able to output
        # absolute resistance level values, but cannot yet be used due
        # to an internal restriction in esphome
        # resistor: 100 kOhm

Configuration variables:
------------------------

- **id** (**Required**, :ref:`config-id`): The id to use for this output component.
- **cs_pin** (**Optional**, int): The SPI chip select pin to use
- All other options from :ref:`Output <config-output>`.


See also
--------

- :doc:`/components/output/mcp4xxx`
- :doc:`/components/output/index`
- :ghedit:`Edit`
