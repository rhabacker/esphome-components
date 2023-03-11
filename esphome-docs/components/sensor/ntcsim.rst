NTC Sensor simulation
=====================

.. seo::
    :description: Instructions for setting up NTC thermistor simulation sensor in ESPHome
    :image: ntc.jpg

The ``ntcsim`` platform is an auxiliary sensor that allows temperature readings to be
converted into resistance readings that simulate an NTC thermistor, which can be used
in place of a real NTC thermistor with a digital potentiometer or dac.

The temperature reading

First, you need to get temperature readings from the sensor - you can set this up with sensors
that provide temperatures.

This platform will then convert the temperature values to resistance readings.
It also requires calibration parameters for this conversion. There are two
ways of obtaining these values: By looking at the datasheet or manual calculation.

If you have the datasheet of the thermistor, you can look at its "B-constant" and
reference temperature/resistance. For example `this product <https://www.adafruit.com/product/372>`__
would have the following calibration configuration.

.. code-block:: yaml

    # Example configuration entry
    sensor:
      - platform: ntcsim
        # ...
        calibration:
          b_constant: 3950
          reference_temperature: 25°C
          reference_resistance: 10kOhm

If you don't have access to the datasheet or want to calculate these values yourself,
you have to first measure three resistance values at different temperatures.
Heat/cool the NTC to three different temperatures (best if temperatures are far apart)
and write down the resistance readings at those temperatures. Then enter these values in the
calibration parameter:

.. code-block:: yaml

    # Example configuration entry
    sensor:
      - platform: ntcsim
        # ...
        calibration:
          - 10.0kOhm -> 25°C
          - 27.219kOhm -> 0°C
          - 14.674kOhm -> 15°C

.. code-block:: yaml

    # Example configuration entry
    sensor:
      - platform: ntcsim
        sensor: temperature_sensor
        output: resistance_output
        # required to normalize output value (0-1)
        output_resistance: 100 kOhm
        calibration:
          b_constant: 3950
          reference_temperature: 25°C
          reference_resistance: 10kOhm
        name: NTC Resistance simulation

      # Example source sensors:
      ...

Configuration variables:
------------------------

- **sensor** (**Required**, :ref:`config-id`): The sensor to read the temperature values from
  to convert to resistance readings.
- **output** (**Optional**, :ref:`output`): The output to send resistance readings to.
- **output_resistance** (**Optional**, :ref:`float`): NTC resistance value by which the value sent
  to the output is divided. Scaling is required as the output component can only receive values
  between 0 and 1.
- **calibration** (**Required**, float): The calibration parameters of the sensor - see above
  for more details.
- All other options from :ref:`Sensor <config-sensor>`.

See Also
--------

- :ref:`sensor-filters`
- :apiref:`ntcsim/ntcsim.h`
- :ghedit:`Edit`
