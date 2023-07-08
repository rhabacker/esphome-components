MCP42xx Output
==============

.. seo::
    :description: Instructions for setting up MCP42xx outputs on the ESP.
    :image: mcp4xxx.jpg

The MCP4xxx output component (`datasheet<https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/22060b.pdf>`,
`Digi-Key<https://www.digikey.de/en/products/detail/microchip-technology/mcp4252-503e-p/1635667>`)
enables access to a specific potentiometer of an MCP4xxx type integrated circuit.

.. code-block:: yaml

    # Example configuration entry

    # Setup a mcp4xxx device using the SPI bus
    mcp4xxx:
        id: mcp4xxx_chip
        # optional
        # cs_pin: SS
        # resistor value cannot be used caused by an internal esphome limitation
        # resistor: 100 kOhm

    # Set the output to use the two pots of a mcp42x2
    output:
      - platform: mcp4xxx
        id: pot_1
        mcp4xxx_id: mcp4xxx_chip
        channel: A
      - platform: mcp4xxx
        id: pot_2
        mcp4xxx_id: mcp4xxx_chip
        channel: B

    # Example usage
    on_...:
      then:
        - output.set_level:
            id: pot1
            level: 50%
        - output.set_level:
            id: dac_output
            level: 10%

Configuration variables:
------------------------

- **id** (**Required**, :ref:`config-id`): The id to use for this output component.
- **channel** (**Required**, int): The channel to use (A or B)
- All other options from :ref:`Output <config-output>`.


See also
--------

- :doc:`/components/output/index`
- :doc:`/components/mcp4xxx`
- :ghedit:`Edit`
