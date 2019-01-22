import React from 'react';
import './sidebar.css';

const sidebar = () => {
    return (<div className="sideBar">
        <a href="#">Send Alert</a>
        <a href="#">Edit Alert</a>
        <a href="#">Cancel Alert</a>
        <a href="#">View Alerts</a>
    </div>);
};

export default sidebar;