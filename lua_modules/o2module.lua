
local bootstrap_module = {}
setmetatable(bootstrap_module, { __index = _ENV })

_ENV = bootstrap_module

function create(extra)
    local new_module = {}
    if extra then
        if type(extra) == "function" then
            extra(new_module)
        elseif type(extra) == "table" then
            setmetatable(new_module, { __index = extra })
        end
    end
    return new_module
end




