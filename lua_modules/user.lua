
local old_require = require
function require(mod_name)
    _ENV[mod_name] = old_require(mod_name)
end
--test = require "test"
require "test"

print(test)

test.f()

for k,v in pairs(_ENV) do
    print(k,v)
end

