import React, { Component } from 'react';
import {
  Collapse,
  Navbar,
  NavbarToggler,
  NavbarBrand,
  Nav,
  NavItem,
  NavLink,
  UncontrolledDropdown,
  DropdownToggle,
  DropdownMenu,
  DropdownItem } from 'reactstrap';

export default class Header extends Component {
  constructor(props) {
    super(props);

    this.toggle = this.toggle.bind(this);
    this.state = {
      isOpen: false
    };
  }

  toggle() { this.setState({ isOpen: !this.state.isOpen }); }

  render() {
    return (
      <div>
        <Navbar color="dark" dark fixed='true' expand="md">
          <NavbarToggler onClick={this.toggle} />
          <NavbarBrand href="/"><b>OS-WASABI </b>CADG</NavbarBrand>
          <Collapse isOpen={this.state.isOpen} navbar>
            <Nav className="ml-auto" navbar>
              <UncontrolledDropdown nav inNavbar>
                <DropdownToggle nav caret>
                  Originators
                </DropdownToggle>
                <DropdownMenu right>
                  <DropdownItem>
                    Manage
                  </DropdownItem>
                  <DropdownItem divider />
                  <DropdownItem>
                    Add
                  </DropdownItem>
                </DropdownMenu>
              </UncontrolledDropdown>
              <UncontrolledDropdown nav inNavbar>
                <DropdownToggle nav caret>
                  Disseminators
                </DropdownToggle>
                <DropdownMenu right>
                  <DropdownItem>
                    Manage
                  </DropdownItem>
                  <DropdownItem divider />
                  <DropdownItem>
                    Add
                  </DropdownItem>
                </DropdownMenu>
              </UncontrolledDropdown>
              <NavItem>
                <NavLink href="/login"><b>Login</b></NavLink>
              </NavItem>
            </Nav>
          </Collapse>
        </Navbar>
      </div>
    );
  }
}