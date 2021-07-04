function [theta, sse]=ellipseFit(data)
% Ellipse fitting

center0=...		% Initial guess of the center
center=fminsearch(@(x)sseOfEllipseFit(x, data), center0);	% Use fminsearch to find the best value of x (center)
...

% Function that returns SSE and the linear parameters
function [sse, radius]=sseOfEllipseFit(center, data)
% Put your function body here...
...