package Cdk::Scroll;

@ISA	= qw (Cdk);

#
# This creates a new Scroll object.
#
sub new
{
   my $type		= shift;
   my %params		= @_;
   my $self		= {};
   my $name		= "${type}::new";

   # Retain the type of the object.
   $self->{'Type'}	= $type;
   
   # Set up the parameters passed in.
   my $title = Cdk::checkReq ($name, "Title", $params{'Title'});
   my $list = Cdk::checkReq ($name, "List", $params{'List'});
   my $height = Cdk::checkReq ($name, "Height", $params{'Height'});
   my $width = Cdk::checkReq ($name, "Width", $params{'Width'});
   my $xpos = Cdk::checkDef ($name, "Xpos", $params{'Xpos'}, "CENTER");
   my $ypos = Cdk::checkDef ($name, "Ypos", $params{'Ypos'}, "CENTER");
   my $numbers = Cdk::checkDef ($name, "Numbers", $params{'Numbers'}, "FALSE");
   my $highlight = Cdk::checkDef ($name, "Highlight", $params{'Highlight'}, "A_REVERSE");
   my $box = Cdk::checkDef ($name, "Box", $params{'Box'}, "TRUE");
   my $shadow = Cdk::checkDef ($name, "Shadow", $params{'Shadow'}, "FALSE");

   # Create the thing.
   $self->{'Me'} = Cdk::Scroll::New ($title,
					$params{'List'},
					$height, $width, $xpos, $ypos,
					$numbers, $highlight,
					$box, $shadow);
   bless $self;
}

#
# This activates the object
#
sub activate
{
   my $self		= shift;
   my %params		= @_;
   my $name		= "$self->{'Type'}::activate";

   # Activate the object...
   if (defined $params{'Input'})
   {
      $self->{'Info'} = Cdk::Scroll::Activate ($self->{'Me'}, $params{'Input'});
   }
   else
   {
      $self->{'Info'} = Cdk::Scroll::Activate ($self->{'Me'});
   }
   return ($self->{'Info'});
}

#
# This injects a character into the widget.
#
sub inject
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::inject";

   # Set the values.
   my $character = Cdk::checkReq ($name, "Input", $params{'Input'});

   return (Cdk::Scroll::Inject ($self->{'Me'}, $character));
}

#
# This adds a line to the scrolling list.
#
sub add
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::add";

   # Set the values.
   my $item = Cdk::checkReq ($name, "Item", $params{'Item'});
   Cdk::Scroll::Add ($self->{'Me'}, $item);
}

#
# This deletes a line from the scrolling list.
#
sub delete
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::delete";

   # Set the values.
   my $position = Cdk::checkReq ($name, "Position", $params{'Position'});
   Cdk::Scroll::Delete ($self->{'Me'}, $position);
}

#
# This allows us to bind a key to an action.
#
sub bind
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::bind";
 
   # Set the values.
   my $key = Cdk::checkReq ($name, "Key", $params{'Key'});
   my $function = Cdk::checkReq ($name, "Function", $params{'Function'});
   Cdk::Scroll::Bind ($self->{'Me'}, $key, $params{'Function'});
}

#
# This draws the object.
#
sub draw
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::draw";

   # Set up the parameters passed in.
   my $box = Cdk::checkDef ($name, "Box", $params{'Box'}, "BOX");
   
   # Draw the object.
   Cdk::Scroll::Draw ($self->{'Me'}, $box);
}

#
# This sets certain attributes of the scrolling list.
#
sub set
{
   my $self	= shift;
   my %params	= @_;
   my $name	= "$self->{'Type'}::set";

   # Set the required values.
   my $list = Cdk::checkReq ($name, "List", $params{'List'});
   my $number = Cdk::checkDef ($name, "Numbers", $params{'Numbers'}, "FALSE");
   my $highlight = Cdk::checkDef ($name, "Highlight", $params{'Highlight'}, "A_REVERSE");
   my $box = Cdk::checkDef ($name, "Box", $params{'Box'}, "TRUE");

   Cdk::Scroll::Set ($self->{'Me'}, $params{'List'}, $number, $highlight, $box);
}

#
# This erases the object.
#
sub erase
{
   my $self	= shift;
   Cdk::Scroll::Erase ($self->{'Me'});
}

#
# This function raises the object.
#
sub raise
{
   my $self	= shift;
   Cdk::Scroll::Raise ($self->{'Me'});
}

#
# This function lowers the object.
#
sub lower
{
   my $self	= shift;
   Cdk::Scroll::Lower ($self->{'Me'});
}

#
# This function registers the object.
#
sub register
{
   my $self	= shift;
   Cdk::Scroll::Register ($self->{'Me'});
}

#
# This function unregisters the object.
#
sub unregister
{
   my $self	= shift;
   Cdk::Scroll::Unregister ($self->{'Me'});
}

#
# This function returns the pointer to the window.
#
sub getwin
{
   my $self	= shift;
   Cdk::Scroll::GetWindow ($self->{'Me'});
}

#
# This function returns the size of the scrolling list and the
# currently highlighted item.
#
sub info
{
   my $self	= shift;
   return Cdk::Scroll::Info ($self->{'Me'});
}

1;
