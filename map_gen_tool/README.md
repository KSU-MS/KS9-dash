The python script 'main.py' here should get ran with the platformIO build action, it looks in its directory for a file called map_target.csv and generates te_delta_tool.hpp and puts that into the include file to be used, there should be a toggle for this feature in parameters.hpp.

## More info
> This next bit isn't true yet btw

It expects the CSV to be in the following format
|...|...|latitude|longitude|...|
|--:|--:|-------:|--------:|--:|
|xxx|xxx|33.93819|-84.52264|xxx|

# TODO
- [ ] Get it generating a useful thingy
- [ ] Make LVGL widgets
- [ ] Get example working on device
- [ ] Make some more supporting tools for map triming
- [ ] Improve embedded code look up algos
- [ ] Get the dash to do this by itself?
