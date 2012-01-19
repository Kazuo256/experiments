
--module("test", package.seeall)

local t = {}
setmetatable(t, { __index = _ENV })
local function change_env(tab)
    _ENV = tab
end

--_ENV = t
change_env(t)

local function p()
    print "HEY"
end

function f()
    p()
end

return _ENV

