
--require "base"

base = proto

local v = base.vec2()

v:add(base.vec2(1,2))

print(v:x(), v:y())

function ls(t)
  for k,v in pairs(t) do
    print(k,v)
  end
end

print "~~~~~~~~~~~~~~~~~~~"

ls(base)

print(exported:x(), exported:y())


