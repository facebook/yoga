import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import Playground from './Playground';
import Demo from './Demo';

const components = {Playground, Demo};
window.onload = function() {
  document.querySelectorAll('react').forEach(node => {
    const props = JSON.parse(node.getAttribute('props'));
    if (components[node.getAttribute('component')]) {
      ReactDOM.render(
        React.createElement(
          components[node.getAttribute('component')],
          props,
          node.innerHTML,
        ),
        node,
      );
    } else {
      console.error(
        `Component "${node.getAttribute(
          'component',
        )}" could not be found. Exported components are ${Object.keys(
          components,
        ).join(', ')}`,
      );
    }
  });
};
